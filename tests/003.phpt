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
$ret = cracklib_check("SkonkyJimIsAFiend");
var_dump($ret);
$ret = cracklib_check("5k0nky", "skonky");
var_dump($ret);
$ret = cracklib_check("j3nk1n5", "george", "Jenkins the Man");
var_dump($ret);
?>
--EXPECT--
array(2) {
  ["ok"]=>
  bool(true)
  ["reason"]=>
  string(11) "Password OK"
}
array(2) {
  ["ok"]=>
  bool(false)
  ["reason"]=>
  string(28) "it is based on your username"
}
array(2) {
  ["ok"]=>
  bool(false)
  ["reason"]=>
  string(36) "it is based upon your password entry"
}
