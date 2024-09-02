{
  stdenv,
  lib,
  cmake,
  doxygen,
  graphviz,
  enableStatic ? false,
  enableShared ? !enableStatic,
  enaleTests ? true,
  enableDoc ? true,
}:

assert enableShared || enableStatic;

stdenv.mkDerivation (finalAttrs: {
  pname = "tinyhash";
  version = "0.0.1";

  src = ./.;

  cmakeFlags =
    lib.optional enaleTests "-DBUILD_TESTS=ON"
    ++ lib.optional enableStatic "-DBUILD_STATIC=ON"
    ++ lib.optional enableDoc ''
      -DBUILD_DOC=ON
      -DDOT_BIN_PATH=${graphviz}/bin/dot
    '';

  nativeBuildInputs = [ cmake ];

  buildInputs = [ doxygen ];

  postBuild = lib.optionals enaleTests ''
    make test
  '';

  postInstall = lib.optionals enaleTests ''
    mkdir $out/doc

    for dir in "html" "latex"; do
      mv doc/$dir $out/doc/$dir
    done
  '';

  meta = {
    description = "This is a library containing multiple C implementations of hashmap.";
    homepage = "https://github.com/theobori/${finalAttrs.pname}";
    license = lib.licenses.mit;
  };
})
