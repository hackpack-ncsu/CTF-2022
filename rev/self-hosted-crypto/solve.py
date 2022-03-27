with open("output", 'rb') as f:
	contents = f.read()
	output = bytes(c - 0xD for c in contents)
	print(output)
