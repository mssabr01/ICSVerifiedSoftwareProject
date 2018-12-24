{-# LANGUAGE CPP #-}
{-# OPTIONS_GHC -fno-warn-missing-import-lists #-}
{-# OPTIONS_GHC -fno-warn-implicit-prelude #-}
module Paths_capDL_tool (
    version,
    getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

#if defined(VERSION_base)

#if MIN_VERSION_base(4,0,0)
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#else
catchIO :: IO a -> (Exception.Exception -> IO a) -> IO a
#endif

#else
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#endif
catchIO = Exception.catch

version :: Version
version = Version [1,0,0,1] []
bindir, libdir, dynlibdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/hello-camkes-1/parse_capdl_tool-prefix/src/parse_capdl_tool-build/.stack-work/install/x86_64-linux/lts-9.21/8.0.2/bin"
libdir     = "/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/hello-camkes-1/parse_capdl_tool-prefix/src/parse_capdl_tool-build/.stack-work/install/x86_64-linux/lts-9.21/8.0.2/lib/x86_64-linux-ghc-8.0.2/capDL-tool-1.0.0.1"
dynlibdir  = "/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/hello-camkes-1/parse_capdl_tool-prefix/src/parse_capdl_tool-build/.stack-work/install/x86_64-linux/lts-9.21/8.0.2/lib/x86_64-linux-ghc-8.0.2"
datadir    = "/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/hello-camkes-1/parse_capdl_tool-prefix/src/parse_capdl_tool-build/.stack-work/install/x86_64-linux/lts-9.21/8.0.2/share/x86_64-linux-ghc-8.0.2/capDL-tool-1.0.0.1"
libexecdir = "/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/hello-camkes-1/parse_capdl_tool-prefix/src/parse_capdl_tool-build/.stack-work/install/x86_64-linux/lts-9.21/8.0.2/libexec"
sysconfdir = "/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/hello-camkes-1/parse_capdl_tool-prefix/src/parse_capdl_tool-build/.stack-work/install/x86_64-linux/lts-9.21/8.0.2/etc"

getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "capDL_tool_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "capDL_tool_libdir") (\_ -> return libdir)
getDynLibDir = catchIO (getEnv "capDL_tool_dynlibdir") (\_ -> return dynlibdir)
getDataDir = catchIO (getEnv "capDL_tool_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "capDL_tool_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "capDL_tool_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
