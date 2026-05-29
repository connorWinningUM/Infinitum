extends Node

@export var bn: BigNumber

func _ready() -> void:
	bn = BigNumber.new()
	print("====== Testing BigNumber Properties ======")
	test_properties();
	print("====== Testing BigNumber Set Value =======")

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

# Assumes that the get_int 
func test_set_value() -> int:
	Engine.print_error_messages = false
	var total_failures: int = 0
	Engine.print_error_messages = true
	return total_failures
