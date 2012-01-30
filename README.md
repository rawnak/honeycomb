Honeycomb Toolkit
=========

Honeycomb is a cross-platform application framework. The objective of this framework is to allow application developers to write and compile their code once and have the ability to run it natively in various runtimes. This ability is achieved through dynamic code generation, as opposed to code recompilations that is commonly used by other projects with similar goals.

License
-------
This library is free software released under the GNU Lesser General Public License. See the LICENSE file located in the root directory of the source tree for details.

Building
-------
Assuming you are running a Linux system with git and cmake installed, you can download and build honeycomb with the following commands:

```bash
$ git clone https://github.com/rawnak/honeycomb.git
$ mkdir honeycomb/build
$ cd honeycomb/build
$ cmake ..
$ make bootstrap
$ make
```

