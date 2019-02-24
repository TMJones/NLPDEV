import sys
import MeCab
#sysとmecab-python3を呼び出します。

m = MeCab.Tagger ("-Ochasen")
'''
mecabインスタンスの生成(出力フォーマットはchasen)
ヨミ：("-Oyomi")
全情報：("-Odump")
わかち書き：("-O wakati")
etc...　公式ドキュメント見てください。
'''

text = input(">>")
lines = m.parse(text).splitlines()
for line in lines:
  if line == "EOS":
    break
  param = line.split("\t")
  print(param[0] + " " + param[3])

