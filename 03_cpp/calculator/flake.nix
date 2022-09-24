{
  inputs = {
    nixpkgs = {
      url = "github:nixos/nixpkgs/nixos-unstable";
    };
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
  };
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
        calculator = (with pkgs; stdenv.mkDerivation {
          pname = "calculator";
          version = "2.0.0";
          meta.mainProgram = "calculator";
          src = ./.;
          nativeBuildInputs = [
            cmake
            clang
          ];
          buildPhase = ''
            make -j $NIX_BUILD_CORES
          '';
          installPhase = ''
            mkdir -p $out/bin/
            mv calculator $out/bin/
          '';
        });
      in rec {
        defaultApp = flake-utils.lib.mkApp {
          drv = defaultPackage;
        };
        defaultPackage = calculator;
        devShell = pkgs.mkShell {
          buildInputs = [
            calculator
          ];
        };
      }
    );
}
