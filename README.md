# Reader-Writer-Problem

## Description

There is a memory area that can be read and written. Several threads have access to it, while at the same time they can read as many threads as they want, but only one can write. How to provide such an access mode?

In this solution, the reader has unhindered access to the memory while it is open for reading. Writers can wait as long as they want
