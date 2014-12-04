(function() { 'use strict';

    localStorage['aaa'] = '000';
    localStorage.setItem('bbb', '111');
    print('getItem "aaa" = ' + localStorage.getItem('aaa'));
    print('getItem "bbb" = ' + localStorage.getItem('bbb'));

})();
