## Install utilities
package 'wget'
package 'openssh-server'
package 'vim'
package 'silversearcher-ag'
package 'git'
package 'curl'
package 'libjpeg-dev'

execute 'update_packages' do
  command 'apt-get update'
end

## Install pip3, pip and pexpect

package 'python3-pip'
package 'python-pip'
package 'rabbitmq-server'

## Install Django

execute 'install_Django' do
  command 'pip3 install Django'
end

## Install Django Rest
execute 'install_djangorestframework' do
  command 'pip3 install djangorestframework'
end

## Filtering support
execute 'install_django-filter' do
  command 'pip3 install django-filter'
end

execute 'install_celery' do
  command 'pip install celery'
end

execute 'clone backend repository' do
  command 'git clone https://github.com/arturbersan/bag_of_task.git'
  cwd 'home/vagrant'
  ignore_failure true
end
