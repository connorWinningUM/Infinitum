extends Node

@export var bn: BigNumber

func _ready() -> void:
	bn = BigNumber.new()
	print("====== Testing BigNumber Properties ======")
	BigNumberPropertyTests.test_properties()
	print("==== Testing BigNumber Value Methods =====")
	BigNumberValueTests.test_value()

func test_arithmatic() -> int:
	Engine.print_error_messages = false
	var total_failures: int = 0
	
	var other: BigNumber = BigNumber.new()
	
	Engine.print_error_messages = true
	return total_failures
