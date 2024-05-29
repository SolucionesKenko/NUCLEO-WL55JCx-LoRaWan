import base64

def base64_encode_binary(input_bytes):
    # Encode the bytes using Base64
    encoded_bytes = base64.b64encode(input_bytes)
    
    # Convert the encoded bytes back to a string
    encoded_string = encoded_bytes.decode('utf-8')
    
    return encoded_string

# Test the function with binary value '1' (0x01)
input_bytes = b'\x01'
encoded_string = base64_encode_binary(input_bytes)
print("Encoded string:", encoded_string)
