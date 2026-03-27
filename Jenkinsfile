pipeline {
    agent none

    stages {
        stage("Build") {
            parallel {

                stage("Windows build") {
                    agent { label "windows" }
                    stages {
                        stage("Checkout") {
                            steps { checkout scm }
                        }
			stage("fetch cedev"){
				steps {
					bat "if exists CEdev rmdir /s /q CEdev"
					bat "if exists CEdev-Windows.zip del CEdev-Windows.zip"
					bat "curl -L -O https://github.com/CE-Programming/toolchain/releases/download/v14.2/CEdev-Windows.zip"
					pwsh "Expand-Archive -Path CEdev-Windows.zip -DestinationPath CEdev"
                        stage("Build") {
                            steps {
				bat """
					CEdev\\CEdev\\cedev.bat
					make
				"""
                            }
                        }
			stage("archive"){
				steps {
					archiveArtifacts artifacts: 'bin/**', fingerprint: true
				}
			}
                    }
                }

                stage("Linux build") {
                    agent { label "linux" }
                    stages {
                        stage("Checkout") {
                            steps { checkout scm }
                        }
			stage("Fetch CEdev"){
				steps {
					sh "[ -d CEdev ] && rm -rf CEdev"
					sh "[ -f CEdev-Linux.tar.gz ] && rm CEdev-Linux.tar.gz"
					sh "curl -L -O https://github.com/CE-Programming/toolchain/releases/download/v14.2/CEdev-Linux.tar.gz"
					sh "tar -xzvf CEdev-Linux.tar.gz"
				}
                        stage("Build") {
                            steps {
                                sh "make"
                            }
                        }
			stage("archive"){
				steps {
					archiveArtifacts artifacts: 'bin/**', fingerprint: true
				}
			}
                    }
                }

            }
        }
    }
}

