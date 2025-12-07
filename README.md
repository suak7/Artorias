<div align="center">
  
# Custom x86 Bootloader

**x86 bootloader with USB driver support**

| Start Date  | End Date |
| ------------- | ------------- |
| December 5, 2025  | Unknown  |

</div>
<p>A bootloader written from scratch that loads a second-stage loader, prints messages in both 16-bit and 32-bit modes, switches to protected mode, and lays the foundation for USB driver support.</p>

## Requirements
- x86_64-elf Cross-Compiler
- GNU Make
- NASM 
- QEMU

## Building
```bash
make all    # Build boot sector and disk image
make run    # Run in QEMU
```

## Resources
- [OSDev Wiki - Rolling Your Own Bootloader](<https://wiki.osdev.org/Rolling_Your_Own_Bootloader>)
- [Carnegie Mellon University - Writing a Bootloader from Scratch](<https://www.cs.cmu.edu/~410-s07/p4/p4-boot.pdf>)


## License

This project is licensed under the Apache License 2.0. See the [LICENSE](./LICENSE) file for details.
