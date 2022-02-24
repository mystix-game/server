extends Server

# Called when the node enters the scene tree for the first time.
func _ready():
	test_func()
	start_server(4242)
	
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
