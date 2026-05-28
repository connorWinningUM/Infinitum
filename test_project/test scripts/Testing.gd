class_name Testing
extends RefCounted

# returns 1 if false, 0 if true
static func check_equal(expected: Variant, actual: Variant, error_doc: String) -> int:
	Engine.print_error_messages = true
	if expected != actual:
		printerr("  ↳ ❌ ASSERTION FAILED: %s (Expected %s, got %s)" % [error_doc, str(expected), str(actual)])
		Engine.print_error_messages = false
		return 1 # Return 1 failure count
	Engine.print_error_messages = false
	return 0
