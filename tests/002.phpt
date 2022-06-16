--TEST--
crack_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('crack')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = crack_test1();

var_dump($ret);
?>
--EXPECT--
The extension crack is loaded and working!
NULL
