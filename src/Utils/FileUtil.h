//
//  FileUtil.h
//  Mural
//
//  Created by Sean on 12/4/14.
//
//

#ifndef __Mural__FileUtil__
#define __Mural__FileUtil__

#include <string>
#include <vector>

namespace mural {

    typedef std::string String;
    typedef std::vector<String> StringList;

    /**
     * Gets the entire contents of a file with each line separated for you.
     *  (Doesn't do smart streaming, so don't pass it bajigabyte sized files.)
     *
     * @param fileName The path to the file to load
     * @param outList A StringList to which the file's lines will be appended,
     *   with each line being its own value.
     * @return True if we could read the file, false if we couldn't
     */
    bool getLinesFromFile(const String& fileName, StringList& outList);

    /**
     * Writes a set of lines to a file. Will wipe out any existing file contents.
     *
     * @param fileName The path of the file to write to
     * @param strings The StringList to be written (each string will get its
     *   own line)
     * @return True if we could write to the file, false if we couldn't
     */
    bool writeLinesToFile(const String& fileName, const StringList& strings);

    /**
     * Appends a set of lines to a file.
     *
     * @param fileName The path of the file to append to
     * @param strings The StringList to be append (each string will get its
     *   own line)
     * @return True if we could write to the file, false if we couldn't
     */
    bool appendLineToFile(const String& fileName, const String& line);

    /**
     * Ensures that a path of directories exists -- returns true if it does,
     *  false if it doesn't (if, for example, the program doesn't have
     *  sufficient permissions to create the path).
     *
     * @param path The path to create
     * @return Whether it actually exists at the end of this function
     */
    bool makeDirectories(const String& path);

    /**
     * Convenience function for reading an entire file as a single string.
     *  If there is no such file, and empty string will be returned.
     *
     * @param fileName The file to read
     * @return The complete text of the file
     */
    const String readWholeFile(const String& fileName);

    /**
     * Gives a system-appropriate writable directory for the use of logs,
     *  preference files, etc.
     *
     * @return The path to the defined writable directory.
     */
    const String getStorageDirectory();

    /**
     * Returns a path to the My Documents directory on Windows, or the
     *  ~/Documents folder on Mac. On Linux? Who knows?!
     *
     * @return Path to the user's documents
     */
    const String getDocumentsPath();

    /**
     * Gives the name of the current executable.
     *
     * @return The name of the current executable
     */
    const String getExeName();

    /**
     * Returns the modification time of a file. Defined as number of seconds
     *  after a system-specific epoch, so not portable between operating
     *  systems, but useful for comparisons within a single build.
     *
     * @param fileName The file to check
     * @return The modification time of the file. Returns 0 if file could
     *   not be found. NOTE: this actually *is* a valid modification time,
     *   so apologies if you happen to have a file that was modified exactly
     *   on your epoch time.
     */
    const long getModificationTime(const String& fileName);

    /**
     * Splits a long string into a StringList.
     *
     * @param splitMe The string to split up
     * @param splitChars The set of delimiter characters to use for the splitting
     * @param bRemoveEmptyEntries Whether or not empty strings (resulting from
     *   multiple delimiters) should be added to the return list
     * @return The list of strings derived from the split
     */
    StringList splitString(const String& splitMe, const String& splitChars, bool bRemoveEmptyEntries = true);

    /**
     * Splits a long string into a StringList wherever newlines or tabs appear.
     *
     * @param splitMe The string to split
     * @return The list of strings derived from the split
     */
    StringList splitString(const String& splitMe);
}

#endif /* defined(__Mural__FileUtil__) */
