from hashlib import sha512,sha1
import random,sys,struct
import SocketServer
import base64 as b64
import os
import hmac
from time import time
 


class HandleCheckin(SocketServer.BaseRequestHandler):
	N = 59244860562241836037412967740090202129129493209028128777608075105340045576269119581606482976574497977007826166502644772626633024570441729436559376092540137133423133727302575949573761665758712151467911366235364142212961105408972344133228752133405884706571372774484384452551216417305613197930780130560424424943100169162129296770713102943256911159434397670875927197768487154862841806112741324720583453986631649607781487954360670817072076325212351448760497872482740542034951413536329940050886314722210271560696533722492893515961159297492975432439922689444585637489674895803176632819896331235057103813705143408943511591629
	accepted={}
	def hashToInt(self,*params):
		sha=sha512()
		for el in params:
			sha.update("%r"%el)
		return int(sha.hexdigest(), 16)
	def cryptrand(self,n=2048):  
		p1=self.hashToInt(os.urandom(40))<<1600
		p1+=self.hashToInt(p1)<<1000
		p1+=self.hashToInt(p1)<<500
		p1+=self.hashToInt(p1)
		bitmask=((2<<(n+1))-1)
		p1=(p1&bitmask)
		return  (p1% self.N)
	def sendInt(self,toSend):
		s=hex(toSend)
		s=s[2:]
		if s[-1]=="L":
			s=s[:-1]
		self.request.sendall(s+"\n")
	def readInt(self):
		req=self.request
		leng = struct.unpack("H", req.recv(2))[0]
		if leng>520:
			req.sendall("Sorry that is too long a number\n")
			req.close()
			return None
		toRead = ""
		while len(toRead) < leng:
			toRead += req.recv(leng - len(toRead))
		if len(toRead) > leng:
			req.sendall("Ain't happenin today dave\n")
			req.close()
			return None
		return int(toRead,16)
		
	def checkBlacklist(self):
		foreign=self.request.getpeername()[0]
		if foreign in self.accepted:
			while(len(self.accepted[foreign]) >0 and
				self.accepted[foreign][0]<time()-600):
				del self.accepted[foreign][0]
			if len(self.accepted[foreign])>5:
				self.request.send("Too many requests too quick sorry\n")
				self.request.close()
				return False
		else:
			self.accepted[foreign]=[]
		return True

	def doChallenge(self):
		req=self.request

		proof = b64.b64encode(os.urandom(12))
		req.sendall("You must first solve a puzzle, a sha1 sum ending in 24 bit's set to 1, it must be of length %s bytes, starting with %s" % (len(proof)+5, proof))
		test = req.recv(21)

		ha = sha1()
		ha.update(test)

		if(not self.checkBlacklist()):
			return False
		if (test[0:16] != proof or 
			ha.digest()[-3:] != "\xff\xff\xff"):
			req.sendall("NOPE")
			req.close()
			return False

		self.accepted[self.request.getpeername()[0]].append(time())

		return True

	def getClientParams(self):
		N=self.N
		req=self.request
		index=self.readInt()
		if index is None:
			return
		if index<2 or index>N/2:#we don't have nearly that many users, we wish we did but lets be honest ,brute force attempt
			req.sendall("A Wrong move against the motherland\n")
			req.close()
			return None
		req.sendall("Please provide your ephemeral key, can never be too careful\n")
		cEphemeral=self.readInt()
		if cEphemeral is None:
			return None
		if  cEphemeral%N==0:
			req.sendall("The Wrong move against the motherland\n")
			req.close()
			return None
		return cEphemeral,index

	def doSlurp(self,index,cEphemeral,salt):
		N=self.N

		password = ""
		hashToInt= self.hashToInt
		salt=hashToInt(index)

		storedKey = pow(index, hashToInt(salt, password), N)
		multiplierSlush = 3
		
		sEphemeralPriv = self.cryptrand()
		sEphemeral = (multiplierSlush * storedKey + 
			pow(index, sEphemeralPriv, N)) % N
		
		self.sendInt(salt)
		self.sendInt(sEphemeral)
		
		slush = hashToInt(cEphemeral, sEphemeral)
		agreedKey = hashToInt(pow(cEphemeral * pow(storedKey, slush, N), sEphemeralPriv, N))
		return agreedKey,sEphemeral

	def handle(self):
		N=self.N
		hashToInt=self.hashToInt
		req = self.request
		if(not self.doChallenge()):
			return

		req.sendall("Welcome to Arstotzka's check in server, please provide the agent number\n")

		cEphemeral,index=self.getClientParams()

		salt=self.hashToInt(index)
		agreedKey,sEphemeral=self.doSlurp(index,cEphemeral,salt)

		gennedKey=hashToInt(hashToInt(N) ^ hashToInt(index), hashToInt(index), salt, 
			cEphemeral, sEphemeral, agreedKey)

		check=self.readInt()

		if(check==gennedKey):
			req.sendall("Well done comrade, the key to the vault is {} \n")

		req.close()

class ThreadedServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
	pass

if __name__ == "__main__":
	HOST, PORT = "", int(sys.argv[1])
	server = ThreadedServer((HOST, PORT), HandleCheckin)
	server.allow_reuse_address = True
	server.serve_forever()
