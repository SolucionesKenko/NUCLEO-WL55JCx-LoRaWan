import base64

# Your array here
hex_data = bytearray([0xB0, 0x11, 0x00, 0x00, 0x12, 0x56, 0x03])

# Convert to base64
base64_encoded = base64.b64encode(hex_data).decode('utf-8')
print(base64_encoded)
