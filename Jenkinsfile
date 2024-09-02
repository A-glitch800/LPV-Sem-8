pipeline {
    agent any

    stages {
        stage('Dev') {
            steps {
                echo 'Hello Dev'
                bat 'git clone "https://github.com/A-glitch800/LPV-Sem-8.git"'
            }
        }
        stage('QA') {
            steps {
                echo 'Hello QA'
            }
        }
        stage('UAP') {
            steps {
                echo 'Hello UAP'
            }
        }
        stage('Prod') {
            steps {
                echo 'Hello Prod'
            }
        }
        stage('Test') {
            steps {
                echo 'Hello Test'
            }
        }
    }
}
