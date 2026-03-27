pipeline {
    agent none
    tools {
	com.cloudbees.jenkins.plugins.customtools.CustomTool 'cedev'
    }

    stages {
        stage("Build") {
            parallel {

                stage("Windows build") {
                    agent { label "windows" }
                    stages {
                        stage("Checkout") {
                            steps { checkout scm }
                        }
                        stage("Build") {
                            steps {
                                bat "make"
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

