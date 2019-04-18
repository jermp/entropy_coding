Entropy coding
-----------------

A C++ implementation of entropy coding algorithms,
such as Shannon-Fano [1,2] and Huffman [3].

Compile with:

	mkdir build
	cd build
	cmake ..
	make

From inside `build`, run

	./build [type] ../test/alphabet --verbose

where `[type]` is `shannon_fano` or `huffman` to generate the corresponding code for the 26-letter
alphabet.

References
----------
[1] C. E. Shannon, *A mathematical theory of communication*. Bell system technical journal 27.3 (1948): 379-423.

[2] R. M. Fano, *The transmission of information*. Cambridge, Massachusetts Institute of Technology, Research Laboratory of Electronics, 1949.

[3] D. A. Huffman, *A method for the construction of minimum-redundancy codes*.
Proceedings of the IRE 40, 9
(1952): 1098–1101.