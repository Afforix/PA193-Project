{  
    "id": "a9561eb1b190625c9adb5a9513e72c4dedafc1cb2d4c5236c9a6957ec7dfd5a9",
    "parent": "c6e3cedcda2e3982a1a6760e178355e8e65f7b80e4e5248743fa3549d284e024",
    "checksum": "tarsum.v1+sha256:e58fcf7418d2390dec8e8fb69d88c06ec07039d651fedc3aa72af9972e7d046b",
    "created": "2014-10-13T21:19:18.674353812Z",
    "author": "Alyssa P. Hacker &ltalyspdev@example.com&gt",
    "architecture": "amd64",
    "os": "linux",
    "Size": 271828,
    "config": {
        "User": "alice",
        "Memory": 2048,
        "MemorySwap": 4096,
        "CpuShares": 8,
        "ExposedPorts": {  
            "8080/tcp": {}
        },
        "Env": [  
            "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
            "FOO=docker_is_a_really",
            "BAR=great_tool_you_know"
        ],
        "Entrypoint": [
            "/bin/my-app-binary"
        ],
        "Cmd": [
            "--foreground",
            "--config",
            "/etc/my-app.d/default.cfg"
        ],
        "Volumes": {
            "/var/job-result-data": {},
            "/var/log/my-app-logs": {}
        },
        "WorkingDir": "/home/alice"
    }
}
