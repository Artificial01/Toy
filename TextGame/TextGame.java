import java.util.Scanner;
abstract class Beings{
    abstract int getLife(int level,int weapon);
    abstract int getDefence(int level,int weapon);
    abstract int getAttack(int level,int weapon);
    abstract String getName();
}
abstract class Spirit extends Beings{
    abstract double getSuperAttackRate(int level);
    abstract int skill(int number1,int number2);
}
abstract class Monster extends Beings{
    abstract int getExperience();
    abstract int getMoney();
}
class BlueSilverGrass extends Spirit{
    public int getLife(int level,int weapon){
        switch(weapon){
            case 0:
                return level*12+60;
            case 1:
                return level*12+60+5;
            case 2:
                return level*12+60+200;
            case 3:
            case 4:
                return level*12+60+50;
            case 5:
                return level*12+60+5000;
            default:
                return 0;
        }
    }
    public int getDefence(int level,int weapon){
        switch(weapon){
            case 0:
                return level*4+20;
            case 1:
                return level*4+20+5;
            case 2:
            case 3:
                return level*4+20+50;
            case 4:
                return level*4+20+200;
            case 5:
                return level*4+20+5000;
            default:
                return 0;
        }
    }
    public int getAttack(int level,int weapon){
        switch(weapon){
            case 0:
                return level*5+25;
            case 1:
                return level*5+25+10;
            case 2:
            case 4:
                return level*5+25+50;
            case 3:
                return level*5+25+200;
            case 5:
                return level*5+25+5000;
            default:
                return 0;
        }
    }
    public String getName(){
        return "Blue Silver Grass";
    }
    public double getSuperAttackRate(int level){
        return level*0.01;
    }
    public int skill(int number1,int number2){
        return number1-number2*2;
    }
}
class SkyHammer extends Spirit{
    public int getLife(int level,int weapon){
        switch(weapon){
            case 0:
                return level*20+100;
            case 1:
                return level*20+100+5;
            case 2:
                return level*20+100+200;
            case 3:
            case 4:
                return level*20+100+50;
            case 5:
                return level*20+100+5000;
            default:
                return 0;
        }
    }
    public int getDefence(int level,int weapon){
        switch(weapon){
            case 0:
                return level+5;
            case 1:
                return level+5+5;
            case 2:
            case 3:
                return level+5+50;
            case 4:
                return level+5+200;
            case 5:
                return level+5+5000;
            default:
                return 0;
        }
    }
    public int getAttack(int level,int weapon){
        switch(weapon){
            case 0:
                return level*6+30;
            case 1:
                return level*6+30+10;
            case 2:
            case 4:
                return level*6+30+50;
            case 3:
                return level*6+30+200;
            case 5:
                return level*6+30+5000;
            default:
                return 0;
        }
    }
    public String getName(){
        return "Sky Hammer";
    }
    public double getSuperAttackRate(int level){
        return level*0.02;
    }
    public int skill(int number1,int number2){
        return number1+number2/3;
    }
}
class SixWingAngel extends Spirit{
    public int getLife(int level,int weapon){
        switch(weapon){
            case 0:
                return level*16+80;
            case 1:
                return level*16+80+5;
            case 2:
                return level*16+80+200;
            case 3:
            case 4:
                return level*16+80+50;
            case 5:
                return level*16+80+5000;
            default:
                return 0;
        }
    }
    public int getDefence(int level,int weapon){
        switch(weapon){
            case 0:
                return level*3+15;
            case 1:
                return level*3+15+5;
            case 2:
            case 3:
                return level*3+15+50;
            case 4:
                return level*3+15+200;
            case 5:
                return level*3+15+5000;
            default:
                return 0;
        }
    }
    public int getAttack(int level,int weapon){
        switch(weapon){
            case 0:
                return level*5+25;
            case 1:
                return level*5+25+10;
            case 2:
            case 4:
                return level*5+25+50;
            case 3:
                return level*5+25+200;
            case 5:
                return level*5+25+5000;
            default:
                return 0;
        }
    }
    public String getName(){
        return "Six Wing Angel";
    }
    public double getSuperAttackRate(int level){
        return level*0.015;
    }
    public int skill(int number1,int number2){
        return number1+number2*2;
    }
}
class DarkKing extends Spirit{
    public int getLife(int i,int j){
        return 5000;
    }
    public int getDefence(int i,int j){
        return 500;
    }
    public int getAttack(int i,int j){
        return 1000;
    }
    public String getName(){
        return "Dark King";
    }
    public double getSuperAttackRate(int i){
        return 0.5;
    }
    public int skill(int number1,int number2){
        return 0;
    }
}
class SmallMonster extends Monster{
    public int getLife(int i,int j){
        return 20;
    }
    public int getDefence(int i,int j){
        return 20;
    }
    public int getAttack(int i,int j){
        return 30;
    }
    public String getName(){
        return "Tree Demon";
    }
    public int getExperience(){
        return 5;
    }
    public int getMoney(){
        return 25;
    }
}
class MiddleMonster extends Monster{
    public int getLife(int i,int j){
        return 40;
    }
    public int getDefence(int i,int j){
        return 40;
    }
    public int getAttack(int i,int j){
        return 60;
    }
    public String getName(){
        return "Cruel Wolf";
    }
    public int getExperience(){
        return 20;
    }
    public int getMoney(){
        return 100;
    }
}
class LargeMonster extends Monster{
    public int getLife(int i,int j){
        return 100;
    }
    public int getDefence(int i,int j){
        return 100;
    }
    public int getAttack(int i,int j){
        return 150;
    }
    public String getName(){
        return "Rock Giant";
    }
    public int getExperience(){
        return 35;
    }
    public int getMoney(){
        return 175;
    }
}
class UltimateMonster extends Monster{
    public int getLife(int i,int j){
        return 200;
    }
    public int getDefence(int i,int j){
        return 200;
    }
    public int getAttack(int i,int j){
        return 300;
    }
    public String getName(){
        return "Death God";
    }
    public int getExperience(){
        return 80;
    }
    public int getMoney(){
        return 400;
    }
}
public class AVG{
    public static Spirit summonSpirit(){
        Scanner input=new Scanner(System.in);
        System.out.println("Choose spirit:1-Blue Silver Grass 2-Sky Hammer 3-Six Wing Angel");
        int choice=input.nextInt();
        switch(choice){
            case 1:
                BlueSilverGrass spirit1=new BlueSilverGrass();
                System.out.println("Summon Blue Silver Grass successfully!");
                System.out.println();
                showStatus1(spirit1,0,0);
                return spirit1;
            case 2:
                SkyHammer spirit2=new SkyHammer();
                System.out.println("Summon Sky Hammer successfully!");
                System.out.println();
                showStatus1(spirit2,0,0);
                return spirit2;
            case 3:
                SixWingAngel spirit3=new SixWingAngel();
                System.out.println("Summon Six Wing Angel successfully!");
                System.out.println();
                showStatus1(spirit3,0,0);
                return spirit3;
            default:
                System.out.println("You are killed by the spirit summoned!");
                System.out.println("- - -End- - -");
                return null;
        }
    }
    public static void tapToContinue(){
        Scanner input=new Scanner(System.in);
        System.out.println("- - - - - - - tap to continue - - - - - - -");
        input.next();
    }
    public static void showStatus1(Spirit spirit,int level,int weapon){
        System.out.println("Name:"+spirit.getName());
        System.out.println("Life:"+spirit.getLife(level,weapon));
        System.out.println("Defence:"+spirit.getDefence(level,weapon));
        System.out.println("Attack:"+spirit.getAttack(level,weapon));
        System.out.println("Super Attack Rate:"+spirit.getSuperAttackRate(level));
        System.out.print("Occupied Weapon:");
        switch(weapon){
            case 0:
                System.out.println("no weapon");
                break;
            case 1:
                System.out.println("abandoned sword");
                break;
            case 2:
                System.out.println("spring of demon");
                break;
            case 3:
                System.out.println("hammer of war");
                break;
            case 4:
                System.out.println("shield of diamond");
                break;
            case 5:
                System.out.println("SUPREME AUTHORITY");
                break;
        }
        System.out.println();
        if(spirit instanceof BlueSilverGrass){
            System.out.print("The spirit is offensive and defensive");
        }else if(spirit instanceof SkyHammer){
            System.out.print("The spirit has awesome strength");
        }else if(spirit instanceof SixWingAngel){
            System.out.print("The spirit has strong vitality");
        }
        System.out.print(" ");
        if(level<=10){
            System.out.println("Now it is potential");
        }else if(level<=20){
            System.out.println("Now it is thriving");
        }else if(level<=30){
            System.out.println("Now it is strong");
        }else{
            System.out.println("Now it is powerful");
        }
        System.out.println();
    }
    public static void showStatus2(int positionX,int positionY,Spirit spirit,int level,int experience,int money,int weapon){
        System.out.println();
        System.out.println("Space:("+positionX+","+positionY+")");
        System.out.println("Level:"+level);
        System.out.println("Experience:"+experience);
        System.out.println("Money:"+money);
        showStatus1(spirit,level,weapon);
    }
    public static void showMap(){
        System.out.println();
        System.out.println("*******************************");
        System.out.println("***   |?|     |o|     |?|   ***");
        System.out.println("**          (GORGE)          **");
        System.out.println("*                             *");
        System.out.println("*             |^|             *");
        System.out.println("*                             *");
        System.out.println("*             |^|             *");
        System.out.println("*                             *");
        System.out.println("*     |!|     |o|     |!|     *");
        System.out.println("*    (FIR)  (PLAIN)  (MER)    *");
        System.out.println("*                             *");
        System.out.println("*             |^|             *");
        System.out.println("*                             *");
        System.out.println("*             |^|             *");
        System.out.println("*                             *");
        System.out.println("*     |!|     |o|     |!|     *");
        System.out.println("*    (MAP)  (FOREST) (SWO)    *");
        System.out.println("*                             *");
        System.out.println("*             |^|             *");
        System.out.println("**                           **");
        System.out.println("***           |+|           ***");
        System.out.println("*******************************");
        System.out.println();
    }
    public static int[] map(int positionX,int positionY,Spirit spirit,int level,int experience,int money,int weapon){
        Monster smallMonster=new SmallMonster();
        Monster middleMonster=new MiddleMonster();
        Monster largeMonster=new LargeMonster();
        Monster ultimateMonster=new UltimateMonster();
        int[] experience_money_weapon={experience,money,weapon};
        switch(positionX){
            case 0:
                switch(positionY){
                    case 1:
                    case 4:
                        return fightWithMonster(spirit,smallMonster,level,experience,money,weapon);
                    case 2:
                        System.out.println("****************************");
                        System.out.println("** Welcome To Star Forest **");
                        System.out.println("****************************");
                        return fightWithMonster(spirit,smallMonster,level,experience,money,weapon);
                    case 3:
                        return fightWithMonster(spirit,middleMonster,level,experience,money,weapon);
                    case 5:
                        System.out.println("***************************");
                        System.out.println("** Welcome To Wild Plain **");
                        System.out.println("***************************");
                        return fightWithMonster(spirit,middleMonster,level,experience,money,weapon);
                    case 6:
                    case 7:
                        return fightWithMonster(spirit,largeMonster,level,experience,money,weapon);
                    case 8:
                        System.out.println("****************************");
                        System.out.println("** Welcome To Death Gorge **");
                        System.out.println("****************************");
                        return fightWithMonster(spirit,ultimateMonster,level,experience,money,weapon);
                    case 9:
                        return fightWithMonster(spirit,ultimateMonster,level,experience,money,weapon);
                    case 11:
                        darkKingdom(spirit,level,weapon);
                        return null;
                    default:
                        System.out.println("Nothing is here");
                        return experience_money_weapon;
                }
            case -1:
                switch(positionY){
                    case 2:
                        System.out.println("Find a map");
                        tapToContinue();
                        showMap();
                        return experience_money_weapon;
                    case 5:
                        System.out.println("You are killed by fire balls coming from sky");
                        System.out.println("- - -End- - -");
                        return null;
                    case 8:
                        System.out.println("Find a mysterious place");
                        tapToContinue();
                        experience_money_weapon[2]=mystery1(weapon);
                        return experience_money_weapon;
                    default:
                        System.out.println("Nothing is here");
                        return experience_money_weapon;
                }
            case 1:
                switch(positionY){
                    case 2:
                        System.out.println("Find a abandoned sword");
                        tapToContinue();
                        experience_money_weapon[2]=1;
                        return experience_money_weapon;
                    case 5:
                        System.out.println("Find an odd merchant");
                        tapToContinue();
                        return merchant(experience,money,weapon);
                    case 8:
                        System.out.println("Find a mysterious place");
                        tapToContinue();
                        experience_money_weapon[1]=mystery2(money);
                        return experience_money_weapon;
                    default:
                        System.out.println("Nothing is here");
                        return experience_money_weapon;
                }
            default:
                System.out.println("Nothing is here");
                return experience_money_weapon;
        }
    }
    public static int[] fightWithMonster(Spirit spirit,Monster monster,int level,int experience,int money,int weapon){
        Scanner input=new Scanner(System.in);
        int battleTimes=1;
        int harmSpirit=monster.getAttack(0,0)-spirit.getDefence(level,weapon);
        int harmMonster=spirit.getAttack(level,weapon)-monster.getDefence(0,0);
        int spiritLife=spirit.getLife(level,weapon);
        int monsterLife=monster.getLife(0,0);
        tapToContinue();
        System.out.println("Meet with "+monster.getName());
        while((spiritLife>0)&&(monsterLife>0)){
            System.out.println("Attack or Escape");
            String choice=input.next();
            double randomNumber1=Math.random();
            if(choice.equals("a")){
                System.out.println("Attack successfully!");
            }else if(choice.equals("e") &&(randomNumber1>0.5)){
                System.out.println("Escape successfully!");
                break;
            }else if(choice.equals("e") &&(randomNumber1<=0.5)){
                System.out.println("Fail to escape!");
                spiritLife-=harmSpirit;
                System.out.println("Your life:"+spiritLife);
            }else{
                System.out.println("Nothing done!");
                spiritLife-=harmSpirit;
                System.out.println("Your life:"+spiritLife);
            }
            tapToContinue();
            System.out.println("Battle Times:"+battleTimes);
            double randomNumber2=Math.random();
            if(randomNumber2<spirit.getSuperAttackRate(level)){
                System.out.println("Super Attack!");
                monsterLife-=(harmMonster*2);
            }else{
                monsterLife-=harmMonster;
            }
            spiritLife-=harmSpirit;
            System.out.print("Skill:");
            if(spirit instanceof BlueSilverGrass){
                System.out.println("Rage!");
                monsterLife=spirit.skill(monsterLife,harmMonster);
            }else if(spirit instanceof SkyHammer){
                System.out.println("Weaken!");
                harmMonster=spirit.skill(harmMonster,monster.getDefence(0,0));
            }else if(spirit instanceof SixWingAngel){
                System.out.println("Recover!");
                spiritLife=spirit.skill(spiritLife,spirit.getAttack(level,weapon));
            }
            System.out.println();
            System.out.println("Your life:"+spiritLife);
            System.out.println("Monster's life:"+monsterLife);
            System.out.println();
            battleTimes++;
        }
        tapToContinue();
        System.out.println("Battle Over!");
        if(spiritLife<=0){
            System.out.println("You are killed by the monster!");
            System.out.println("- - -End- - -");
            return null;
        }
        tapToContinue();
        System.out.println("Monster are killed!");
        System.out.println("Gain money:"+monster.getMoney());
        System.out.println("Gain experience:"+monster.getExperience());
        return new int[]{experience+monster.getExperience(),money+monster.getMoney(),weapon};
    }
    public static int[] increaseLevel(int level,int experience){
        if(level>=experience){
            return new int[]{level,experience};
        }else{
            System.out.println("Level Up!");
            return increaseLevel(level+1,experience-level);
        }
    }
    public static int[] merchant(int experience,int money,int weapon){
        Scanner input=new Scanner(System.in);
        int[] experience_money_weapon={experience,money,weapon};
        System.out.println("Here are some weapons:");
        System.out.println("number\tweapon\tprice");
        System.out.println("1\tspring of demon\t750");
        System.out.println("2\thammer of war\t1250");
        System.out.println("3\tshield of diamond\t1000");
        int choice=input.nextInt();
        switch(choice){
            case 1:
                experience_money_weapon[1]-=750;
                experience_money_weapon[2]=2;
                System.out.println("Gain spring of demon successfully!");
                break;
            case 2:
                experience_money_weapon[1]-=1250;
                experience_money_weapon[2]=3;
                System.out.println("Gain hammer of war successfully!");
                break;
            case 3:
                experience_money_weapon[1]-=1000;
                experience_money_weapon[2]=4;
                System.out.println("Gain shield of diamond successfully!");
                break;
            default:
                System.out.println("Good bye");
                break;
        }
        if(experience_money_weapon[1]<0){
            System.out.println("You owe a debt!");
        }
        return experience_money_weapon;
    }
    public static int mystery1(int weapon){
        double fortune=Math.random();
        if(fortune<0.1){
            System.out.println("Light Falls On You!");
            tapToContinue();
            System.out.println("Gain SUPREME AUTHORITY!");
            return 5;
        }else{
            System.out.println("Find a note");
            tapToContinue();
            System.out.println("It reads:Horrible Danger!Don't go to the space (0,11)!");
            return weapon;
        }
    }
    public static int mystery2(int money){
        double fortune=Math.random();
        if(fortune<0.5){
            System.out.println("Good Fortune!");
            tapToContinue();
            System.out.println("Gain 1000 money!");
            return money+1000;
        }else{
            System.out.println("Bad Fortune!");
            tapToContinue();
            System.out.println("Lose all money");
            return 0;
        }
    }
    public static void darkKingdom(Spirit spirit,int level,int weapon){
        DarkKing darkKing=new DarkKing();
        int darkKingLife=darkKing.getLife(0,0);
        int spiritLife=spirit.getLife(level,weapon);
        double darkKingSuperAttackRate=darkKing.getSuperAttackRate(0);
        double spiritSuperAttackRate=spirit.getSuperAttackRate(level);
        int harmDarkKing=spirit.getAttack(level,weapon)-darkKing.getDefence(0,0);
        int harmSpirit=darkKing.getAttack(0,0)-spirit.getDefence(level,weapon);
        System.out.println("*******************************");
        System.out.println("** Welcome To Space Of Chaos **");
        System.out.println("*******************************");
        tapToContinue();
        System.out.println("Here is a dark spirit");
        System.out.println("It sits on throne silently seeming to wait for something");
        tapToContinue();
        System.out.println("After long");
        System.out.println("It sighs before saying:please beat me or you will die");
        tapToContinue();
        while((darkKingLife>0)&&(spiritLife>0)){
            double randomNumber1=Math.random();
            double randomNumber2=Math.random();
            if(randomNumber1<darkKingSuperAttackRate){
                spiritLife-=harmSpirit*2;
            }else{
                spiritLife-=harmSpirit;
            }
            if(randomNumber2<spiritSuperAttackRate){
                darkKingLife-=harmDarkKing*2;
            }else{
                darkKingLife-=harmDarkKing;
            }
            System.out.println("Dark spirit waves its sword and it hurts you");
            System.out.println("Your life:"+spiritLife);
            tapToContinue();
            if(spiritLife>0){
                System.out.println("You are still alive and fight back fiercely");
                System.out.println("Dark spirit's life:"+darkKingLife);
            }
            tapToContinue();
        }
        if(spiritLife>0){
            System.out.println("Now you are still alive with dark spirit lying beside you");
            tapToContinue();
            System.out.println("Dark spirit says:You won't get out of space of chaos");
            tapToContinue();
            System.out.println("Dark spirit says:You will live alone until one coming here kills you");
            tapToContinue();
            System.out.println("Dark spirit says:You will become me");
            tapToContinue();
            System.out.println("It's your destiny!");
            tapToContinue();
            System.out.println("- - -End- - -");
            tapToContinue();
            surprise();
        }else{
            System.out.println("You are killed by dark spirit");
            System.out.println("- - -End- - -");
        }
    }
    public static void surprise(){
        System.out.println("Surprise!");
        tapToContinue();
        System.out.println();
        System.out.println("        *        ");
        for(int i=0;i<9;i++){
            System.out.println("       ***       ");
        }
        System.out.println("    *********    ");
        System.out.println("    *********    ");
        System.out.println("       ***       ");
        System.out.println("       ***       ");
        System.out.println();
        System.out.println(" abandoned sword ");
        System.out.println();
        tapToContinue();
        System.out.println();
        System.out.println("    *********    ");
        System.out.println(" ***         *** ");
        System.out.println("*      ***      *");
        System.out.println(" **   * * *   ** ");
        System.out.println("   ***  *  ***   ");
        for(int i=0;i<5;i++){
            System.out.println("        *        ");
        }
        System.out.println("       ***       ");
        System.out.println("      ** **      ");
        System.out.println("     ** * **     ");
        System.out.println("       ***       ");
        System.out.println();
        System.out.println(" spring of demon ");
        System.out.println();
        tapToContinue();
        System.out.println();
        System.out.println("   **********    ");
        System.out.println(" *************   ");
        System.out.println(" *************   ");
        System.out.println("   **********    ");
        for(int i=0;i<7;i++){
            System.out.println("       ***       ");
        }
        System.out.println("      *****      ");
        System.out.println("      *****      ");
        System.out.println("       ***       ");
        System.out.println();
        System.out.println("  hammer of war  ");
        System.out.println();
        tapToContinue();
        System.out.println();
        System.out.println("   *        *   ");
        System.out.println(" *****    ***** ");
        System.out.println(" ** **    ** ** ");
        System.out.println("****************");
        System.out.println("  ************  ");
        System.out.println("  *****  *****  ");
        System.out.println("  **** ** ****  ");
        System.out.println("  *** ********  ");
        System.out.println("  ****   *****  ");
        System.out.println("  ******* ****  ");
        System.out.println("  *** ** *****  ");
        System.out.println("   ***  *****   ");
        System.out.println("     *****      ");
        System.out.println("      ***       ");
        System.out.println();
        System.out.println("shield of diamond");
        System.out.println();
        tapToContinue();
        System.out.println();
        System.out.println("       ***       ");
        System.out.println("     *******     ");
        System.out.println("    *** * ***    ");
        System.out.println("      *****      ");
        System.out.println("     * *** *     ");
        System.out.println("     * *** *     ");
        System.out.println("     * *** *     ");
        for(int i=0;i<5;i++){
            System.out.println("       ***       ");
        }
        System.out.println("      *****      ");
        System.out.println("     *******     ");
        System.out.println();
        System.out.println("SUPREME AUTHORITY");
        System.out.println();
        tapToContinue();
        System.out.println("That's all");
        System.out.println("Congratulations!");
    }
    public static void main(String[] args){
        Spirit spirit=summonSpirit();
        if(spirit==null){
            tapToContinue();
            System.exit(0);
        }
        int positionX=0,positionY=0;
        int level=0;
        int experience=0;
        int money=0;
        int weapon=0;
        int[] level_experience;
        int[] experience_money_weapon;
        tapToContinue();
        for(;;){
            Scanner input=new Scanner(System.in);
            System.out.println("Go:1-East 2-South 3-West 4-North");
            switch(input.nextInt()){
                case 1:
                    positionX+=1;
                    break;
                case 2:
                    positionY-=1;
                    break;
                case 3:
                    positionX-=1;
                    break;
                case 4:
                    positionY+=1;
                    break;
                default:
                    break;
            }
            experience_money_weapon=map(positionX,positionY,spirit,level,experience,money,weapon);
            if(experience_money_weapon==null){
                tapToContinue();
                System.exit(0);
            }
            experience=experience_money_weapon[0];
            money=experience_money_weapon[1];
            weapon=experience_money_weapon[2];
            level_experience=increaseLevel(level,experience);
            level=level_experience[0];
            experience=level_experience[1];
            System.out.println("Show status or Not");
            if(input.next().equals("s")){
                showStatus2(positionX,positionY,spirit,level,experience,money,weapon);
            }
        }
    }
}
