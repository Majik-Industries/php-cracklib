--TEST--
crack_check() Basic test
--SKIPIF--
<?php
if (!extension_loaded('crack')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = crack_check("oogabooga");

echo $ret["reason"];

var_dump($ret);
?>
--EXPECT--
The extension crack is loaded and working!
NULL
