# -*- coding: utf-8 -*-
# Wordnet via Python3
# 
import sys, sqlite3
from collections import namedtuple
from pprint import pprint

conn = sqlite3.connect("./wnjpn.db")

Word = namedtuple('Word', 'wordid lang lemma pron pos')
Sense = namedtuple('Sense', 'synset wordid lang rank lexid freq src')
Synset = namedtuple('Synset', 'synset pos name src')
SynsetDef = namedtuple('SynsetDef', 'synset lang define sid')
SynLink = namedtuple('SynLink', 'synset1 synset2 link src')

def getWords(lemma):
  cur = conn.execute("select * from word where lemma=?", (lemma,))
  return [Word(*row) for row in cur] 

def getSenses(word):
  cur = conn.execute("select * from sense where wordid=?", (word.wordid,))
  return [Sense(*row) for row in cur]

def getSynset(synset):
  cur = conn.execute("select * from synset where synset=?", (synset,))
  return Synset(*cur.fetchone())

def getSynsetDef(synset, lang):
  cur = conn.execute("select * from synset_def where synset=? and lang=?", (synset, lang))
  return SynsetDef(*cur.fetchone())

def GetSynlinks(synset):
  cur = conn.execute("select * from synlink where synset1=?", (synset,))
  return [SynLink(*row) for row in cur]
  
def getWordsFromSynset(synset, lang):
  cur = conn.execute("select word.* from sense, word where synset=? and word.lang=? and sense.wordid = word.wordid;", (synset,lang))
  return [Word(*row) for row in cur]

def getWordsFromSenses(sense, lang="jpn"):
  synonym = {}
  for s in sense:
    lemmas = []
    syns = getWordsFromSynset(s.synset, lang)
    for sy in syns:
      lemmas.append(sy.lemma)
    synonym[getSynset(s.synset).name] = lemmas
  return synonym

def getSynonyms (word):
    synonym = {}
    words = getWords(word)
    if words:
        for w in words:
            sense = getSenses(w)
            s = getWordsFromSenses(sense)
            synonym = dict(list(synonym.items()) + list(s.items()))
    return synonym

def getConcepts (word, lang="jpn"):
    concepts = {}
    words = getWords(word)
    if words:
        for w in words:
            sense = getSenses(w)
            for s in sense:
                sd = getSynsetDef(s.synset, lang)
                concepts[sd.synset] = sd.define
                
    return concepts

def getLinks (word, lang="jpn"):
    words = getWords(word)
    if words:
        for w in words:
            sense = getSenses(w)
            for s in sense:
                sd = getSynsetDef(s.synset, lang)
                print('【概念】', sd.define)
                synlinks = GetSynlinks(s.synset)
                for sl in synlinks:
                    print('　　[関係]', sl.link, getSynsetDef(sl.synset2, lang).define)
                    syns = getWordsFromSynset(sl.synset2, lang)
                    print(' 　　　(単語)', )
                    for sy in syns:
                        print(sy.lemma + ",", )
                        
                    print("")

    return
            
            
if __name__ == '__main__':
    if len(sys.argv) >= 3:
        if sys.argv[1] == 'GetConcepts':
            concepts = getConcepts(sys.argv[2])
            pprint(concepts)
        elif sys.argv[1] == 'GetSynonyms':
            synonyms = getSynonyms(sys.argv[2])
            pprint(synonyms)
        elif sys.argv[1] == 'GetLinks':
            getLinks(sys.argv[2])
            
            
    else:
        print("パラメータが不足しています")