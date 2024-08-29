{
  stdenv,
  lib,
  cmake,
  enableStatic ? false,
  enableShared ? !enableStatic,
  enaleTests ? true,
}:

assert enableShared || enableStatic;

stdenv.mkDerivation (finalAttrs: {
  pname = "tinyhash";
  version = "0.0.1";

  src = ./.;

  cmakeFlags =
    lib.optional enaleTests "-DBUILD_TESTS=ON"
    ++ lib.optional enableStatic "-DBUILD_STATIC=ON";

  nativeBuildInputs = [ cmake ];

  postBuild = ''
    make test
  '';

  meta = {
    description = "Simple C hash table implementation.";
    homepage = "https://github.com/theobori/${finalAttrs.pname}";
    license = lib.licenses.mit;
  };
})
