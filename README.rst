=========================
PHP Interface to cracklib
=========================

This module was written due to the abandonment of the crack module for PHP. I
had some fundamental issues with the architecture of that module so rather
than port it forward to PHP 7+ this project was born instead.

API
===

The module has a single PHP function it exports ``cracklib_check``::

    $result = cracklib_check($password);

    if (! $result["ok"]) {
        print("Password failed check: ", $result["reason"]);
        die();
    }


Building the module
===================

Building this module depends on having the PHP development files and the
cracklib development files installed on your system.


Compiling
---------

To build the module run the following::

    cd php-cracklib/
    phpize
    ./configure --with-cracklib
    make

    # Install the module
    make install


Post Installation
-----------------

Post installation you'll have to enable the module in PHP.  In your ``php.ini``
file you'll need to add the following line::

    extension=libcrack.so



