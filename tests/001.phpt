--TEST--
Check if test is loaded
--SKIPIF--
<?php
if (!extension_loaded('test')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "test" is available';
?>
--EXPECT--
The extension "test" is available
