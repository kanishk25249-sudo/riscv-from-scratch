data = open('compiler/prog.txt.raw','rb').read()
print('unsigned char prog_bin[] = {')
for i in range(0, len(data), 12):
    chunk = data[i:i+12]
    print('    ' + ', '.join(f'0x{b:02x}' for b in chunk) + ',')
print('};')
print(f'unsigned int prog_bin_len = {len(data)};')