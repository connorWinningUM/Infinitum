extends Node

@export var bn: BigNumber

func _ready() -> void:
	bn = BigNumber.new()
	
	print("Testing BigNumber Properties")
	properties();

func properties() -> void:
	# default precision
	assert(bn.precision == 256)
	
	bn.precision = 257
	assert(bn.precision == 257)
