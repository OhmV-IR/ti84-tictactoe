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

                        stage("Fetch CEdev") {
                            steps {
                                bat "if exist CEdev rmdir /s /q CEdev"
                                bat "if exist CEdev-Windows.zip del CEdev-Windows.zip"
                                bat "curl -L -O https://github.com/CE-Programming/toolchain/releases/download/v14.2/CEdev-Windows.zip"
                                pwsh "Expand-Archive -Path CEdev-Windows.zip -DestinationPath CEdev"
                            }
                        }

                        stage("Build") {
                            steps {
                                script {
                                    env.PATH = "CEdev\\CEdev\\bin;${env.PATH}"
                                }
                                bat "make"
                            }
                        }

                        stage("Archive") {
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

                        stage("Fetch CEdev") {
                            steps {
                                sh  """
					if [ -d CEdev ]; then
						rm -rf CEdev
					fi
					if [ -f CEdev-Linux.tar.gz ]; then
						rm CEdev-Linux.tar.gz
					fi
				"""
                                sh "curl -L -O https://github.com/CE-Programming/toolchain/releases/download/v14.2/CEdev-Linux.tar.gz"
                                sh "tar -xzvf CEdev-Linux.tar.gz"
                            }
                        }

                        stage("Build") {
                            steps {
                                script {
                                    env.PATH = "CEdev/bin:${env.PATH}"
                                }
                                sh "make"
                            }
                        }

                        stage("Archive") {
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

