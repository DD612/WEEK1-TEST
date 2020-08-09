public class Troll extends Monster{
	
	public Troll(String name){
		super(name);
		if(name=="Saul"||name=="Salomon"){
			System.out.println(name+"can't be a proper name.");
			this.name="Detritus";
		}else{
			this.name=name;
		}
}
	public Troll(String name,double spAttackProbability){
		super(name,spAttackProbability);
		if(name=="Saul"||name=="Salomon"){
			System.out.println(name+"can't be a proper name.");
			this.name="Detritus";
		}else{
			this.name=name;
		}
		this.spAttackProbability=spAttackProbability;
}
		public int specialAttack(){
		int x = (int)(Math.random()*15+1);		
		System.out.println(this.name+", of "+this.getClass()+",  hit with a stick :"+x+" points damage caused.");
		return x;
	}
}