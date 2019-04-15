# ft_ssl
MD5 and SHA256 cryptographic hashing functions

Description:\
Maps arbitrary length data (aka message) to fixed sized data (aka hash or digest).\
Hashing functions are designed to make finding two distinct messages that output an\
identical hash computationally infeasible.  MD5 has been discovered to fail this\
requirement.\
Hashes can be used to insure the integrity of transmitted data.
<br/>
<br/>

Usage:\
ft_ssl command [command opts] [command args]

commands\
  md5\
  sha256

command opts\
  -s      &nbsp;&nbsp;&nbsp;&nbsp;Print a checksum of the given string.\
  -p      &nbsp;&nbsp;&nbsp;&nbsp;Echo stdin to stdout and append the checksum to stdout.\
  -q      &nbsp;&nbsp;&nbsp;&nbsp;Quiet mode - only the checksum is printed out.  Overrides the -r option.\
  -r      &nbsp;&nbsp;&nbsp;&nbsp;Reverses the format of the output.  Does nothing when combined with the -p option.

command args\
  string (with -s opt)\
  filename
<br/>
<br/>

Examples:

./ft_ssl md5 -s "hello world"\
MD5 ("hello world") = 5eb63bbbe01eeed093cb22bb8f5acdc3

./ft_ssl md5 -rs "hello world"\
5eb63bbbe01eeed093cb22bb8f5acdc3 "hello world"

./ft_ssl md5 -qs "hello world"\
5eb63bbbe01eeed093cb22bb8f5acdc3

echo -n "hello world" | ./ft_ssl md5 -p\
hello world5eb63bbbe01eeed093cb22bb8f5acdc3

./ft_ssl sha256 -s "hello world"\
SHA256 ("hello world") = b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9

./ft_ssl sha256 -rs "hello world"\
b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9 "hello world"

./ft_ssl sha256 -qs "hello world"\
b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9

echo -n "hello world" | ./ft_ssl sha256 -p\
hello worldb94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9
