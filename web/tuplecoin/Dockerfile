# multistage build; first must use NPM/node to "build" frontend SPA
FROM node:lts-alpine AS builder

# copy in the client subdir
COPY client /build
WORKDIR /build

# build the challenge executable
RUN ls -al
RUN npm install
RUN npm run build

# final stage: build a Python 3 image for running the server
FROM python:3-alpine

# make a normal user to run the challenge as (no running as root!)
RUN addgroup ctfuser && adduser -G ctfuser -h /ctf -D ctfuser

# copy in the static build artifacts from the frontend (and from the project root)
COPY --from=builder /build/dist /ctf/client/dist
COPY code.tar.gz /ctf/client/dist/bkups
COPY robots.txt /ctf/client/dist
WORKDIR /ctf/server

# set up the necessary Python requirements
COPY server/requirements.txt .
RUN pip3 install -r requirements.txt

# copy in the main module to run, and the flag file
COPY server/main.py .
COPY flag.txt .

# run it as our normal user
USER ctfuser
EXPOSE 80
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "80"]
