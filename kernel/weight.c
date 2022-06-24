#include <linux/syscalls.h>
#include <linux/sched/user.h>
#include <linux/uidgid.h>
#include <linux/cred.h>
#include <linux/errno.h>

// int getuserweight(int uid);
SYSCALL_DEFINE1(getuserweight, int, uid)
{
	struct user_struct *user;
	kuid_t setter_uid;

<<<<<<< HEAD
int setuserweight(int uid, int weight); 
*/
SYSCALL_DEFINE1( int, getuserweight, int, uid){
		struct user_struct *user;
		kuid_t setter_uid;
		if (uid==-1) user = get_current_user();
		else{
			setter_uid.val = uid;
			user = find_user(setter_uid);
		} //achando user
		if (user==NULL){
			errno = EINVAL;
			return ERROR; //erro: não achou user
		}
		return user -> weight;
		  
}
SYSCALL_DEFINE2(int, setuserweight, int, uid, int, weight){
		struct user_struct *user,*mod;
		kuid_t setter_uid;
		mod = get_current_user();
		if (uid==-1) user = get_current_user();
		else{
			setter_uid.val = uid;
			user = find_user(setter_uid);
		} //achando user
		if (user==NULL || weight<=0) {
			errno = EINVAL;
			return ERROR; //erro: não achou user ou peso invalido
		}
		else if ((mod->uid).val != 0) {//erro: não é root
			errno = EACCES
			return ERROR;
		}
		user -> weight = weight;
		return 0;
=======
	//achando user
	if (uid == -1) {
		user = get_current_user();
	} else {
		setter_uid.val = uid;
		user = find_user(setter_uid);
	}

	if (user == NULL)
		return -EINVAL; // Erro: não achou user

	return user->weight;
>>>>>>> 03ab694d1179b413e18416075cb9ed3d34c730ff
}

// int setuserweight(int uid, int weight);
SYSCALL_DEFINE2(setuserweight, int, uid, int, weight)
{
	struct user_struct *user, *mod;
	kuid_t setter_uid;

	mod = get_current_user();

	if ((mod->uid).val != 0) // Erro: não é root
		return -EACCES;

	//achando user
	if (uid == -1) {
		user = get_current_user();
	} else {
		setter_uid.val = uid;
		user = find_user(setter_uid);
	}

	if (user == NULL || weight <= 0)
		return -EINVAL; //erro: não achou user

	user->weight = weight;

	return 0;
}
