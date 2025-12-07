<div align="center">
  
# Custom x86 Bootloader

**A x86 bootloader with USB driver support, written from scratch.**

| Start Date  | End Date |
| ------------- | ------------- |
| December 5, 2025  | Unknown  |

</div>

## Requirements
- x86_64-elf Cross-Compiler
- GNU Make
- NASM 
- QEMU

## Building
**Build and Run**
```bash
make all    # Build boot sector and disk image
make run    # Run in QEMU
```

## Resources
- [OSDev Wiki - Rolling Your Own Bootloader](<https://wiki.osdev.org/Rolling_Your_Own_Bootloader>)
- [Carnegie Mellon University - Writing a Bootloader from Scratch](<https://www.cs.cmu.edu/~410-s07/p4/p4-boot.pdf>)


## License

This project is licensed under the Apache License 2.0. See the [LICENSE](./LICENSE) file for details.
