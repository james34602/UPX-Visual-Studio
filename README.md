# UPX-Visual-Studio
Compile UPX and belong librarys in Visual Studio! Source include UCL and zlib

Features:
1. Fully operational build of UPX 3.96, --ultra-brute option available
2. One click project build
3. Editable UPX pe header in conf.h, you can edit UPX0, UPX1 for example

# Improving compression ratio?
Yes, that's pretty simple, LZMA is suggested to be best usable compression method.

There is a few options we can tweak, tracing code from compress_lzma.cpp to conf.h.

We will find pb, lp, lc, num_fast_bytes_t that can be significantly affect compression ratio.

Before adjusting those parameters, make sure you understand the purpose of the parameters, studying LZMA documentary is highly recommended, more importantly tests compression result while tweaking parameters is the best way to get higher compression ratio, there's no 'best' settings or combinations, since specified parameters may suit for text/string compression but not suit for messy periodic data.

### Notice:
Compression ratio would probably ranged within 1-2%.
