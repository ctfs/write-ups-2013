#!/usr/bin/runhaskell
{-# LANGUAGE NoMonomorphismRestriction #-}

import Data.Bits
import Data.Char
import Data.Word
import System.Environment
import Numeric

-- known Collision: "Le1sRI6I"

flag = 0xce97a7b6d709fb62

main = p =<< getArgs
  where p (pwd:_) = print $ dec flag $ toKey pwd
        p _ = return ()

hash :: String -> Word32
hash = fromIntegral.(\(a,b)->(b`shift`16).|.a).foldl r (1, 0)
  where r = \(a,b) x->(a+(ord x.&.0xff),(a+(ord x.&.0xff)+b))

dec :: Word64 -> Word32 -> Word64
dec v k = fin $ foldl r (3337565984,v0,v1) [0..31] where
  v0 = fromIntegral v :: Word32
  v1 = fromIntegral $ v `shiftR` 32 :: Word32
  s' = \a->a-d
  r = \(s,x,y) _-> let y' = update y x  s k (-)
                       x' = update x y' s k (-)
                   in (s' s, x', y')

update = \a b c d f->f a (((b`shift`4) + d)`xor`(b+c)`xor`((b`shiftR`5) + d))
fin = \(_,x,y)->fromIntegral y`shiftL`32.|.(fromIntegral x.&.0xffffffff)

toHexStr s = concat $ "0x":map (flip showHex "".ord) s
toKey s = k0 where
      s' = toHexStr s
      k0 = read ("0x"++(take 8$drop  2 s')) :: Word32


d = 2654435769