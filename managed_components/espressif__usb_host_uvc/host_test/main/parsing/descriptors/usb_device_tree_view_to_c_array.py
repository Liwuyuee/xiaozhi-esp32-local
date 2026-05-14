#!/usr/bin/env python3
# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
import re

def hex_to_c_array(hex_string):
    """
    Converts a hex string (with potential ASCII characters on the right side) into a formatted C-style uint8_t array.

    This function was used for generating C descriptor arrays from USB Device Tree Viewer

    This function:
    1. Removes the ASCII characters from the input, preserving only the hex values.
    2. Cleans up spaces and newlines from the hex values.
    3. Formats the hex values into a C-style uint8_t array with a new line after every 16 bytes.

    Args:
        hex_string (str): The raw hex string input that may contain ASCII characters on the right side.

    Returns:
        str: A formatted C-style uint8_t array string.
    """
    # Step 1: Remove ASCII characters
    # Use regex to capture only the hex part (ignore the part with ASCII characters)
    # cleaned_hex = re.sub(r" {2,}.*", "", hex_string)  # Matches double spaces and removes anything after
    cleaned_hex = re.sub(r"(\S{2}(?:\s\S{2})*)\s{2,}.*", r"\1", hex_string)

    # Step 2: Remove any remaining extra spaces or newlines
    cleaned_hex = cleaned_hex.replace(" ", "").replace("\n", "")

    # Step 3: Split the cleaned hex string into pairs of characters (hex bytes)
    hex_bytes = [cleaned_hex[i:i+2] for i in range(0, len(cleaned_hex), 2)]

    # Step 4: Convert the hex bytes into a C-style uint8_t array with 16 bytes per line
    c_array = "uint8_t data[] = {\n    "
    for i in range(0, len(hex_bytes), 16):
        line = ", ".join(f"0x{byte}" for byte in hex_bytes[i:i+16])
        c_array += line
        if i + 16 < len(hex_bytes):
            c_array += ",\n    "  # Add a newline and indentation if more bytes follow
        else:
            c_array += "\n"
    c_array += "};"

    return c_array

def main():
    """
    The main function where the script execution begins.

    It defines a sample hex string (with ASCII characters on the right side) and converts it
    to a formatted C-style uint8_t array using the hex_to_c_array function.
    """
    # Example input - you can replace this with any hex dump
    hex_string = """
    12 01 00 02 EF 02 01 40 E4 32 15 94 19 04 01 02   .......@.2......
                           03 01                                             ..
    """

    # Convert the hex string to a C array
    c_array_output = hex_to_c_array(hex_string)

    # Print the result
    print(c_array_output)

if __name__ == "__main__":
    main()
