extends Node2D

func _ready() -> void:
	test_big_number()
	test_incrementor()
	pass

func test_big_number():
	var testBig: BigNumber = BigNumber.new()

func test_incrementor():
	var testInc: Incrementor = Incrementor.new()
	testInc.Increment = Vector2(1.0, 2.0);
	print(type_string(typeof(testInc.Increment)));
