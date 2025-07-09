import sys
import os

def bytes_to_c_array(data):
    lines = []
    line = "    "
    for i, byte in enumerate(data):
        line += f"0x{byte:02X}"
        if i != len(data) - 1:
            line += ", "
        if (i + 1) % 16 == 0:
            lines.append(line)
            line = "    "
    if line.strip():
        lines.append(line)
    return "\n".join(lines)

def convert_font_to_header(file_path):
    if not os.path.isfile(file_path):
        return

    with open(file_path, "rb") as f:
        data = f.read()

    filename = os.path.basename(file_path)
    name, _ = os.path.splitext(filename)
    header_filename = f"{name}.h"

    array_declaration = f"unsigned char {name}[] = {{\n{bytes_to_c_array(data)}\n}};"

    with open(header_filename, "w") as header_file:
        header_file.write(array_declaration)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        convert_font_to_header(sys.argv[1])