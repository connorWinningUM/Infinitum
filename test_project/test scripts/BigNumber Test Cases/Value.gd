class_name BigNumberValueTests
extends Node

static func test_value():
	Engine.print_error_messages = false
	
	var total_failures: int = 0
	total_failures += test_setting_values()
	total_failures += test_value_string()
	
	if total_failures == 0:
		print("✅ ALL VALUE TESTS PASSED SUCCESSFULLY!")
	else:
		printerr("❌ %d BigNumber-Value tests failed, see previous logs" % total_failures)
	
	Engine.print_error_messages = true

static func test_setting_values() -> int:
	var bn: BigNumber = BigNumber.new()
	bn.precision = 512
	var total_failures: int = 0
	
	for i in range(100):
		var num: int = randi()
		bn.from_int(num)
		total_failures += Testing.check_equal(num, bn.to_int(), "BigNumber Int value not set correctly")
	
	for i in range(100):
		var num: float = randf()
		bn.from_float(num)
		total_failures += Testing.check_equal(num, bn.to_float(), "BigNumber Float value not set correctly")
	return total_failures

static func test_value_string() -> int:
	var bn: BigNumber = BigNumber.new()
	bn.precision = 512
	var total_failures: int = 0
	
	for i in range(100):
		var num: float = randf()
		bn.from_str(str(num))
		total_failures += Testing.check_equal_float(num, bn.to_float(), "BigNumber from_string not working for floats")
	
	for i in range(100):
		var num: float = randf()
		bn.from_float(num)
		total_failures += Testing.check_equal_float(num, float(bn.to_str(14)), "BigNumber to_string")
	
	for i in range(100):
		var num: int = randi()
		bn.from_int(num)
		total_failures += Testing.check_equal_float(num, int(bn.to_str(14)), "BigNumber to_string")
	
	return total_failures
