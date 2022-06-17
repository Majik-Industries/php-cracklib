--TEST--
cracklib_check() Basic test
--SKIPIF--
<?php
if (!extension_loaded('cracklib')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = cracklib_check("oogabooga");

echo $ret["reason"];

var_dump($ret);
?>
--EXPECT--
The extension cracklib is loaded and working!
NULL
