extends Node

@export var bn: BigNumber

func _ready() -> void:
	bn = BigNumber.new()
	print("====== Testing BigNumber Properties ======")
	test_properties();
	print("====== Testing BigNumber Set Value =======")

func test_properties() -> void:
	var precision_fails: int = test_precision()
	if precision_fails == 0:
		print("✅ ALL TESTS PASSED SUCCESSFULLY!")
	else:
		printerr("❌ %d BigNumber-Pricision tests failed, see previous logs" % precision_fails)

# returns the number of test case failures
func test_precision() -> int:
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
	return total_failures

# Assumes that the get_int 
func test_set_value() -> int:
	Engine.print_error_messages = false
	var total_failures: int = 0
	Engine.print_error_messages = true
	return 0
