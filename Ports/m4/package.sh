#!/usr/bin/env -S bash ../.port_include.sh
port=m4
version=1.4.9
useconfigure=true
files="https://ftpmirror.gnu.org/gnu/m4/m4-${version}.tar.gz m4-${version}.tar.gz
https://ftpmirror.gnu.org/gnu/m4/m4-${version}.tar.gz.sig m4-${version}.tar.gz.sig
https://ftpmirror.gnu.org/gnu/gnu-keyring.gpg gnu-keyring.gpg"
auth_type="sig"
auth_opts=("--keyring" "./gnu-keyring.gpg m4-${version}.tar.gz.sig")
