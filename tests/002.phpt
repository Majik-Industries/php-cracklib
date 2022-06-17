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

var_dump($ret);
?>
--EXPECT--
array(2) {
  ["ok"]=>
  bool(false)
  ["reason"]=>
  string(47) "it does not contain enough DIFFERENT characters"
}
