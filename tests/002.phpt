--TEST--
test_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('test')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = test_test1();

var_dump($ret);
?>
--EXPECT--
The extension test is loaded and working!
NULL
