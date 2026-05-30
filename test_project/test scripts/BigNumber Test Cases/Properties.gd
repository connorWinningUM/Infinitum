class_name BigNumberPropertyTests
extends Node

static func test_properties() -> void:
	Engine.print_error_messages = false
	
	var total_fails: int = _test_precision()
	total_fails += _test_rounding()
	
	if total_fails == 0:
		print("✅ ALL PROPERTY TESTS PASSED SUCCESSFULLY!")
	else:
		printerr("❌ %d BigNumber-Property tests failed, see previous logs" % total_fails)
	
	Engine.print_error_messages = true

static func _test_precision() -> int:
	var bn: BigNumber = BigNumber.new()
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
	
	return total_failures

static func _test_rounding() -> int:
	var bn: BigNumber = BigNumber.new()
	var total_failures: int = 0
	
	total_failures += Testing.check_equal("Nearest", bn.rounding, "BigNumber is not initiailized properly")
	
	var roundTypes = [
		"Nearest", "Toward Zero", "Up", "Down", "Away From Zero"
	];
	for r in roundTypes:
		bn.rounding = r
		total_failures += Testing.check_equal(r, bn.rounding, "BigNumber round type is not set properly")
	
	return total_failures
