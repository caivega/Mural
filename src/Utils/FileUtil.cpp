//
//  FileUtil.cpp
//  Mural
//
//  Created by Sean on 12/4/14.
//
//

#include "FileUtil.h"

#if defined(WIN32)
#include <shlobj.h>
#elif defined(__linux__)
#include <linux/limits.h>
#include <unistd.h>
#endif
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include <sstream>
#include <algorithm>
#include <cctype>

#ifdef WIN32
#define ci_strcmp _stricmp
#endif
#if defined(__APPLE__) || defined(__linux__)
#define ci_strcmp strcasecmp
#include <strings.h>
#endif

using namespace std;

namespace mural
{
    const char StringUtil_WhiteSpaceChars[] = " \t\n\r";

    StringList splitString(const String& splitMe, const String& splitChars, bool bRemoveEmptyEntries /*=true*/)
    {
        StringList retVal;

        //iterate over string
        String buildString;
        for (unsigned int i = 0; i < splitMe.length(); i++) {
            char ch = splitMe[i];
            if (splitChars.find(ch) != String::npos) {
                //Add the build string to our return val
                if (!bRemoveEmptyEntries || buildString.length() > 0)
                    retVal.push_back(buildString);
                buildString.clear();
            }
            else {
                buildString += ch;
            }
        }

        //handle any dangling strings
        if (buildString.length() > 0)
            retVal.push_back(buildString);

        return retVal;
    }

    StringList splitString(const String& splitMe)
    {
        return splitString(splitMe, StringUtil_WhiteSpaceChars);
    }

    bool getLinesFromFile(const String& fileName, StringList& outList)
    {
        ifstream inputFile(fileName.c_str());
        if (inputFile.is_open()) {
            while (!inputFile.eof()) {
                String line;
                getline(inputFile,line);
                outList.push_back(line);
            }
            inputFile.close();
            return true;
        }

        return false;
    }

    const String readWholeFile(const String& fileName)
    {
        String forReturn = "";
        StringList lines;
        getLinesFromFile(fileName, lines);
        for (int i=0; i < lines.size(); i++) {
            forReturn += lines[i];
        }
        return forReturn;
    }

    bool writeLinesToFile(const String& fileName, const StringList& strings)
    {
        ofstream outputFile(fileName.c_str(), ios_base::trunc);
        if (outputFile.is_open()) {
            for (unsigned int i = 0; i < strings.size(); i++) {
                outputFile << strings[i] << endl;
            }
            outputFile.close();
            return true;
        }
        return false;
    }

    bool appendLineToFile(const String& fileName, const String& line)
    {
        ofstream outputFile(fileName.c_str(), ios_base::app);
        if (outputFile.is_open()) {
            outputFile << line << endl;
            outputFile.close();
            return true;
        }
        return false;
    }

    bool makeDirectories(const String& path)
    {
    #if defined(WIN32)
        if (SHCreateDirectoryExA(NULL, path.c_str(), NULL) == ERROR_SUCCESS) {
            return true;
        }
        else {
            return false;
        }
    #else
        char currentDir[PATH_MAX];
        getcwd(currentDir, PATH_MAX);
        chdir("/");
        bool retVal = true;

        StringList elements = splitString(path, "/");
        struct stat statInfo;
        StringList::iterator it = elements.begin();
        String pathAccum;
        while (it != elements.end()) {
            pathAccum += *it;
            if (stat(pathAccum.c_str(), &statInfo) < 0) {
                //path doesn't exist
                if (mkdir(pathAccum.c_str(), S_IRWXU) != 0) {
                    //couldn't be made
                    retVal = false;
                    break;
                }
            }
            if (!S_ISDIR(statInfo.st_mode)) {
                //exists, but it's not a directory
                retVal = false;
                break;
            }

            pathAccum += "/";
            it++;
        }

        chdir(currentDir);
        return retVal;
    #endif
    }

    const String getStorageDirectory()
    {
    #if defined(WIN32)
        return "./";
    #elif defined(__APPLE__)
    #if !BERRY_MOBILE
        String writeDirectory = getenv("HOME");
        writeDirectory += "/Library/Application Support/Mural/" + getExeName() + "/";
        return writeDirectory;
    #else
        NSArray* arrayPaths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
        NSString* docPath = [arrayPaths objectAtIndex:0];
        String writeDirectory = [docPath UTF8String];
        writeDirectory += "/" + GetExeName() + "/";
        return writeDirectory;
    #endif
    #elif defined(__linux__)
        String writeDirectory = getenv("HOME");
        writeDirectory += "/.mural/" + GetExeName() + "/";
        return writeDirectory;
    #endif
    }

    const String getDocumentsPath()
    {
    #if defined(WIN32)
        char myDocs[MAX_PATH];
        HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, myDocs);
        if (result != S_OK) {
            sysLog.Log("ERROR: Couldn't get path to \"My Documents\" directory.");
            return String("");
        }
        else {
            return String(myDocs);
        }
    #elif defined(__APPLE__)
        String path = getenv("HOME");
        return path + "/Documents/";
    #elif defined(__linux__)
        String path = getenv("HOME");
        return path + "/Documents/";
    #endif
    }

    const String getExeName()
    {
        String pathSplit = "/";
    #if defined (WIN32)
        TCHAR exePathWin[MAX_PATH];
        GetModuleFileName( NULL, exePathWin, MAX_PATH );
        String exePath(exePathWin);
        int length = exePath.length();
        if (exePath.substr(length - 4, length) == ".exe") {
            exePath = exePath.substr(0, length - 4);
        }
        pathSplit = "\\";
    #elif defined (__APPLE__)
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef exeURL = CFBundleCopyExecutableURL(mainBundle);
        char exePath[PATH_MAX];
        if (!CFURLGetFileSystemRepresentation(exeURL, TRUE, (UInt8 *)exePath, PATH_MAX)) {
            CFRelease(exeURL);
            printf("Couldn't get exe name.");
            return "";
        }
        CFRelease(exeURL);
    #elif defined (__linux__)
        String exePath = ReadWholeFile("/proc/self/cmdline");
        String splitChars = "";
        splitChars.push_back('\0'); // have to construct null-containing strings carefully
        exePath = SplitString(exePath, splitChars)[0];
    #endif
        
        StringList pathElements = splitString(exePath, pathSplit);
        String exeName = pathElements[pathElements.size()-1];
        
        return exeName;
    }

    const long getModificationTime(const String& fileName)
    {
        struct stat statInfo;
        if (stat(fileName.c_str(), &statInfo) != -1) {
    #if defined(__APPLE__)
            return statInfo.st_mtimespec.tv_sec;
    #else //Linux or Windows
            return statInfo.st_mtime;
    #endif
        }
        else {
            return 0;
        }
    }
}
