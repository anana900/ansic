#!/usr/bin/env groovy
 
node
{
	echo "Welcome!"
	stage('setup')
	{
		try
		{
			echo "Setup"
			sh 'ls -la'	    
		}
		catch(err)
		{
			echo err
		}
	}

	stage('build') 
	{
		try
		{
			echo "Build"
			dir('Debug')
			{
				sh 'make'
			}
    
		}
		catch(err)
		{
			echo err
		}
	}
   
	stage('test') 
	{
		try
		{
			echo "Test"
			dir('Debug')
			{
				sh './ansic'
			} 
		}
		catch(err)
		{
			echo err
		}
	}

	stage('end') 
	{
		try
		{
			echo "Success"
			sh 'ls'    
		}
		catch(err)
		{
			echo err
		}
	}
}
