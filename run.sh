qemu-system-x86_64 -drive format=raw,file=fat:rw:build -drive if=pflash,format=raw,file=OVMF.fd -net none -nographic
