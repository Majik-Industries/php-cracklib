--TEST--
Check if crack is loaded
--SKIPIF--
<?php
if (!extension_loaded('crack')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "crack" is available';
?>
--EXPECT--
The extension "crack" is available
