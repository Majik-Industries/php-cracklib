--TEST--
Check if cracklib is loaded
--SKIPIF--
<?php
if (!extension_loaded('cracklib')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "cracklib" is available';
?>
--EXPECT--
The extension "cracklib" is available
