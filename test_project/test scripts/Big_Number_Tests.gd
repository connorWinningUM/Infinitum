extends Node

@export var bn: BigNumber

func _ready() -> void:
	Engine.print_error_messages = false # prevent the editor from printing errors
	bn = BigNumber.new()
	
	print("====== Testing BigNumber Properties ======")
	properties();

func properties() -> void:
	test_precision()

func test_precision() -> void:
	var total_failures : int = 0
	
	total_failures += Testing.check_equal(256, bn.precision, "BigNumber precision is not initialized properly")
	bn.precision = 0
	total_failures += Testing.check_equal(256, bn.precision, "BigNumber failed to reject precision 0")
	bn.precision = -64
	total_failures += Testing.check_equal(256, bn.precision, "BigNumber failed to reject negative precision")
	bn.precision = 99999999
	total_failures += Testing.check_equal(99999999, bn.precision,
		"BigNumber failed to scale up precision")
	
	if total_failures == 0:
		print("✅ ALL TESTS PASSED SUCCESSFULLY!")
	else:
		printerr("❌ TESTING COMPLETE: %d assertion(s) failed. See logs above." % total_failures)
