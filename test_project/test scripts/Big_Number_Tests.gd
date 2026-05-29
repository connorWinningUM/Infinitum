extends Node

@export var bn: BigNumber

func _ready() -> void:
	bn = BigNumber.new()
	print("====== Testing BigNumber Properties ======")
	test_properties()
	print("====== Testing BigNumber Set Value =======")
	test_value()

func test_properties() -> void:
	var total_fails: int = test_precision()
	total_fails += test_rounding()
	if total_fails == 0:
		print("✅ ALL PROPERTY TESTS PASSED SUCCESSFULLY!")
	else:
		printerr("❌ %d BigNumber-Property tests failed, see previous logs" % total_fails)

# returns the number of test case failures
func test_precision() -> int:
	var originalPrec = bn.precision
	
	Engine.print_error_messages = false
	var total_failures : int = 0
	var prev = bn.precision
	
	total_failures += Testing.check_equal(256, bn.precision, "BigNumber precision is not initialized properly")
	prev = bn.precision
	bn.precision = 0
	total_failures += Testing.check_equal(prev, bn.precision, "BigNumber failed to reject precision 0")
	prev = bn.precision
	bn.precision = -64
	total_failures += Testing.check_equal(prev, bn.precision, "BigNumber failed to reject negative precision")
	bn.precision = 99999999
	total_failures += Testing.check_equal(99999999, bn.precision,
		"BigNumber failed to scale up precision")
	
	Engine.print_error_messages = true
	bn.precision = originalPrec
	return total_failures

func test_rounding() -> int:
	var originalRound = bn.rounding
	Engine.print_error_messages = false
	var total_failures: int = 0
	
	total_failures += Testing.check_equal("Nearest", bn.rounding, "BigNumber is not initiailized properly")
	
	var roundTypes = [
		"Nearest", "Toward Zero", "Up", "Down", "Away From Zero"
	];
	for round in roundTypes:
		bn.rounding = round
		total_failures += Testing.check_equal(round, bn.rounding, "BigNumber round type is not set properly")
	
	Engine.print_error_messages = true
	bn.rounding = originalRound
	return total_failures

func test_value() -> int:
	bn.precision = 512
	Engine.print_error_messages = false
	var total_failures: int = 0
	
	for i in range(100):
		var num: int = randi()
		bn.set_int(num)
		total_failures += Testing.check_equal(num, bn.get_int(), "BigNumber Int value not set correctly")
	
	for i in range(100):
		var num: float = randf()
		bn.set_float(num)
		total_failures += Testing.check_equal(num, bn.get_float(), "BigNumber Float value not set correctly")
	
	for i in range(100):
		var num: int = randi()
		bn.set_str(str(num))
		total_failures += Testing.check_equal(num, bn.get_int(), "BigNumber set_string not working for ints")
	
	for i in range(100):
		var num: float = randf()
		bn.set_str(str(num))
		total_failures += Testing.check_equal_float(num, bn.get_float(), "BigNumber set_string not working for floats")
	
	Engine.print_error_messages = true
	if total_failures == 0:
		print("✅ ALL VALUE TESTS PASSED SUCCESSFULLY!")
	else:
		printerr("❌ %d BigNumber-Value tests failed, see previous logs" % total_failures)
	
	return total_failures

func test_arithmatic() -> int:
	Engine.print_error_messages = false
	var total_failures: int = 0
	
	var other: BigNumber = BigNumber.new()
	
	Engine.print_error_messages = true
	return total_failures
