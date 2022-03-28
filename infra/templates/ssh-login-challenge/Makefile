# change to "ctf2021-${YOUR_CHALLENGE_NAME}"
IMAGE_BASE = ctf2021-ssh-login-challenge

# change to the relative path to your challenge's subfolder of the CTF-2021 git repo
# (this is done so that your Docker builds are always tagged with the git subtree hash
# of your latest committed changes in that specific sub folder, as opposed to the entire
# hash of the latest commit across the entire repo)
SRC_SUBTREE = infra/templates/ssh-login-challenge

# and leave the rest of this alone...
#------------------------------------

IMAGE_TAG = `git rev-parse --verify --short=0 HEAD:${SRC_SUBTREE}`
IMAGE_NAME = $(IMAGE_BASE):$(IMAGE_TAG)


docker:
	docker build -t $(IMAGE_NAME) .
	docker tag $(IMAGE_NAME) $(IMAGE_BASE):latest

install: 
	sh sshsb_conf.sh $(IMAGE_TAG) /etc/ssh-switchboard/conf.d/${IMAGE_BASE}.conf
	docker restart ssh-switchboard

